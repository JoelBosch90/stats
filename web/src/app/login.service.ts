import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders, HttpResponse, HttpXsrfTokenExtractor } from '@angular/common/http';
import { Observable } from 'rxjs/internal/Observable';
import { concatMap } from 'rxjs/operators';

interface Credentials {
  username: string;
  password: string;
}

@Injectable({
  providedIn: 'root'
})
export class LoginService {
  private csrfRequest: Observable<any>;
  
  constructor(private http: HttpClient, private tokenExtractor: HttpXsrfTokenExtractor) {
    // Make sure that we get the XSRF-TOKEN cookie from the server.
    this.csrfRequest = this.http.get('/api/csrf');
    this.csrfRequest.subscribe();
  }

  public async authenticate(credentials: Credentials) {
    const headers = new HttpHeaders({
      'Content-Type': 'application/json'
    });

    this.csrfRequest
      .pipe(concatMap(() => {
        return this.http.post("/api/login", credentials, { headers, observe: 'response', responseType: 'text' });
      }))
      .subscribe((response: HttpResponse<string>) => {
        console.log('response gotten', response.headers);
      });
  }
}
