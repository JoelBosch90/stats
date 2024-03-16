import { Injectable } from '@angular/core';
import { webSocket, WebSocketSubject } from 'rxjs/webSocket';

interface Data {
  loggedIn: boolean;
}

@Injectable({
  providedIn: 'root'
})
export class DataService {
  private store : Data;
  private static readonly DEFAULT_STORE : Data = {
    loggedIn: false
  };
  private webSocket: WebSocketSubject<any> | null = null;

  constructor() {
    const localStore = localStorage.getItem('store');

    try {
      this.store = localStore ? JSON.parse(localStore) : DataService.DEFAULT_STORE;
    } catch {
      this.store = DataService.DEFAULT_STORE;
    }
    
    if (this.get('loggedIn')) this.connect();
  }

  public connect(retries = 3) {
    if (this.webSocket) this.disconnect();

    const protocol = window.location.protocol === 'https:' ? 'wss:' : 'ws:';
    const host = window.location.host;
    const websocketURL = `${protocol}//${host}/api/ws`;
    this.webSocket = webSocket(websocketURL);

    this.webSocket.subscribe({
      next: (message) => console.log(message),
      error: (error) => {
        if (retries) this.connect(retries - 1);
        // It is likely that the session has expired, so we should log out.
        else this.set('loggedIn', false);
        console.log(error)
      },
      complete: () => console.log('complete'),
    });

    return this;
  }

  public disconnect() {
    if (this.webSocket) {
      this.webSocket.complete();
      this.webSocket = null;
    }

    return this;
  }

  public set<Key extends keyof Data>(key: Key, value: Data[Key]) : DataService {
    this.store[key] = value;
    localStorage.setItem('store', JSON.stringify(this.store));

    return this;
  }

  public get<Key extends keyof Data>(key: Key) : Data[Key] {
    return this.store[key];
  }
}
