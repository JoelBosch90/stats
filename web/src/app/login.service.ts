import { Injectable } from '@angular/core';
import { Router } from '@angular/router';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { throwError } from 'rxjs';
import { Observable } from 'rxjs/internal/Observable';
import { concatMap, catchError, tap } from 'rxjs/operators';

interface Credentials {
  username: string;
  password: string;
}

@Injectable({
  providedIn: 'root'
})
export class LoginService {
  private csrfRequest: Observable<any>;
  private loggedIn = true; // TODO: Change this to false after development.
  
  constructor(private http: HttpClient, private router: Router) {
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
        next: () => this.loggedIn = true,
        error: () => this.loggedIn = false
      }),
      catchError((error: unknown) => {
        return throwError(() => error);
      })
    );
  }

  public isLoggedIn() {
    return this.loggedIn;
  }

  public logout() {
    this.loggedIn = false;    
    const logoutObservable = this.http.post("/api/logout", {});

    // Logging out invalidates the CSRF token, so we need to request a new one.
    this.csrfRequest = logoutObservable.pipe(
      concatMap(() => this.requestNewCsrfToken())
    );
    this.csrfRequest.subscribe();

    this.router.navigate(['/login']);
    return logoutObservable;
  }
}
