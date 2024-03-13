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
  private csrfRequest: Observable<any>;
  
  constructor(
    private http: HttpClient,
    private router: Router,
    private dataService: DataService,
    private snackBar: MatSnackBar,
  ) {
    this.csrfRequest = this.requestNewCsrfToken();
    this.csrfRequest.subscribe();
  }

  private requestNewCsrfToken() {
    return this.http.get('/api/csrf');
  }

  public login(credentials: Credentials) {
    const headers = new HttpHeaders({
      'Content-Type': 'application/json'
    });
  
    return this.csrfRequest.pipe(
      concatMap(() => this.http.post("/api/login", credentials, { headers, observe: 'response', responseType: 'text' })),
      tap({
        next: () => this.dataService.set('loggedIn', true),
        error: () => this.dataService.set('loggedIn', false),
      })
    );
  }

  public logout() {
    const logoutObservable = this.http.post("/api/logout", {});

    // Logging out invalidates the CSRF token, so we need to request a new one.
    this.csrfRequest = logoutObservable.pipe(
      concatMap(() => this.requestNewCsrfToken()),
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

    return this.csrfRequest;
  }
}
