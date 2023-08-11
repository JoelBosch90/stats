import { Injectable } from '@angular/core';
import { HttpClient, HttpErrorResponse } from '@angular/common/http';
import { HttpHeaders } from '@angular/common/http';

import { Observable, throwError } from 'rxjs';
import { catchError } from 'rxjs/operators';

interface Credentials {
  username: string;
  password: string;
}

@Injectable({
  providedIn: 'root'
})
export class LoginService {

  constructor(private http: HttpClient) { }

  private handleError(error: HttpErrorResponse) {
    if (error.status === 0) console.error(`The following error occurred: ${error.error}`);
    else console.error(`The request returned the error code ${error.status}, with the body: ${error.error}`);

    return throwError(() => new Error("Could not authenticate. Please try again later."));
  }

  public authenticate(credentials: Credentials): Observable<boolean> {
    const headers = new HttpHeaders({
      'Content-Type': 'application/json',
    });

    return this.http.post<boolean>("/api/login", credentials, { headers })
      .pipe(catchError(this.handleError));
  }
}
