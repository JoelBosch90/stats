import { Injectable } from '@angular/core';

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

  constructor() {
    const localStore = localStorage.getItem('store');

    try {
      this.store = localStore ? JSON.parse(localStore) : DataService.DEFAULT_STORE;
    } catch {
      this.store = DataService.DEFAULT_STORE;
    }
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
