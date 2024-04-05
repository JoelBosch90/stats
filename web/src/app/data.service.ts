import { Injectable } from '@angular/core';
import { Router } from '@angular/router';
import { webSocket, WebSocketSubject } from 'rxjs/webSocket';

interface AccessRecord {
  http_request_fragment: string;
  http_request_path: string;
  http_request_query: string;
  id: number;
  local_time: string;
  remote_address: string;
  remote_user: string;
}

interface Data {
  loggedIn: boolean;
  data: Record<number, AccessRecord>;
}

@Injectable({
  providedIn: 'root'
})
export class DataService {
  private store : Data;
  private static readonly DEFAULT_STORE : Data = {
    loggedIn: false,
    data: {},
  };
  private webSocket: WebSocketSubject<any> | null = null;

  constructor(private router: Router) {
    const localStore = localStorage.getItem('store');

    try {
      this.store = localStore ? JSON.parse(localStore) : DataService.DEFAULT_STORE;
    } catch {
      this.store = DataService.DEFAULT_STORE;
    }
    
    if (this.get('loggedIn')) this.connect();
  }

  public connect(retries?: number) {
    this.resetWebSocket();

    const protocol = window.location.protocol === 'https:' ? 'wss:' : 'ws:';
    const host = window.location.host;
    const websocketURL = `${protocol}//${host}/api/ws`;
    this.webSocket = webSocket(websocketURL);

    this.webSocket.subscribe({
      next: (message: AccessRecord) => {
        const data = this.get('data');

        this.set('data', {...data, [message.id]: message });
      },
      error: (error) => {
        if (error.code === 1006) {
          console.warn('Connection closed unexpectedly. Attempting to reconnect...');
          this.connect(retries ?? 3);
          return;
        }

        if (retries) this.connect(retries - 1);
        // It is likely that the session has expired, so we should log out.
        else this.set('loggedIn', false);
        
        console.error(error);
      },
      complete: () => console.log('WebSocket connection closed.'),
    });
    
    // Send a message 3 seconds after connecting
    setTimeout(() => {
      if (this.webSocket) {
        this.webSocket.next( {
          type: 'catch-up',
          start: null,
        });
      }
    }, 3000);

    this.set('loggedIn', true);
    
    return this;
  }

  public disconnect() {
    this.resetWebSocket();
    this.set('loggedIn', false);
    this.router.navigate(['/login']);

    return this;
  }

  public set<Key extends keyof Data>(key: Key, value: Data[Key]) : DataService {
    this.store[key] = value;
    localStorage.setItem('store', JSON.stringify(this.store));

    return this;
  }

  public get<Key extends keyof Data>(key: Key) : Data[Key] {
    return this.store[key] ?? DataService.DEFAULT_STORE[key];
  }

  private resetWebSocket() {
    if (this.webSocket) {
      this.webSocket.complete();
      this.webSocket = null;
    }
  }
}
