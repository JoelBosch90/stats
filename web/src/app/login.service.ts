import { Injectable } from '@angular/core';
import { Router } from '@angular/router';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { MatSnackBar } from '@angular/material/snack-bar';
import { Observable } from 'rxjs/internal/Observable';
import { concatMap, tap } from 'rxjs/operators';

import { DataService } from './data.service';

interface Credentials {
  username: string;
  password: string;
}

@Injectable({
  providedIn: 'root'
})
export class LoginService {
  constructor(
    private http: HttpClient,
    private router: Router,
    private dataService: DataService,
    private snackBar: MatSnackBar,
  ) {}


  public login(credentials: Credentials) {
    const headers = new HttpHeaders({
      'Content-Type': 'application/json'
    });
  
    return this.http.post("/api/login", credentials, { headers, observe: 'response', responseType: 'text' }).pipe(
      tap({
        next: () => {
          this.dataService.set('loggedIn', true).connect();
        },
        error: () => this.dataService.set('loggedIn', false),
      })
    );
  }

  public logout() {
    return this.http.post("/api/logout", {}).pipe(
      tap({
        next: () => {
          this.dataService.set('loggedIn', false);  
          this.router.navigate(['/login']);
        },
        error: () => {
          this.snackBar.open("Server error: failed to log out.", "Close", {
            duration: 5000,
          });
        }
      })
    );
  }
}
