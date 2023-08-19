import { Injectable } from '@angular/core';
import { HttpClient, HttpErrorResponse, HttpHeaders, HttpResponse } from '@angular/common/http';

import { Observable, throwError, lastValueFrom } from 'rxjs';
import { catchError } from 'rxjs/operators';

interface Credentials {
  username: string;
  password: string;
}

interface CsrfToken {
  headerName: string;
  parameterName: string;
  token: string;
}

@Injectable({
  providedIn: 'root'
})
export class LoginService {
  private csrfPromise: Promise<CsrfToken>;

  constructor(private http: HttpClient) {
    this.csrfPromise = this.getCsrfToken();
  }

  private handleError(error: HttpErrorResponse) {
    if (error.status === 0) console.error(`The following error occurred: ${error.error}`);
    else console.error(`The request returned the error code ${error.status}, with the body: ${error.error}`);

    return throwError(() => new Error("Could not authenticate. Please try again later."));
  }

  private getCsrfToken(): Promise<CsrfToken> {
    const headers = new HttpHeaders({
      'Content-Type': 'text/plain; charset=utf-8',
    });

    const observable = this.http.get<CsrfToken>("/api/csrf", { headers })
      .pipe(catchError(this.handleError));

    return lastValueFrom(observable);
  }

  public async authenticate(credentials: Credentials) {
    const csrf = await this.csrfPromise;
    const headers = new HttpHeaders({
      'Content-Type': 'application/json'
    });

    const requestObservable = this.http.post<any>("/api/login", credentials, { headers, observe: 'response' as 'response' });
    requestObservable.subscribe((response: HttpResponse<any>) => {
      console.log('response gotten', response.headers);
    } );
  }
}
