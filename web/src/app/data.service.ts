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

  public connect() {
    const protocol = window.location.protocol === 'https:' ? 'wss:' : 'ws:';
    const host = window.location.host;
    const websocketURL = `${protocol}//${host}/api/ws`;
    this.webSocket = webSocket(websocketURL);

    this.webSocket.subscribe({
      next: (message) => console.log(message),
      error: (error) => console.log(error),
      complete: () => console.log('complete'),
    });

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
