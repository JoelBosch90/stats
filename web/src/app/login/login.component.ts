import { Component } from '@angular/core';
import { Router } from '@angular/router';
import { AbstractControl, FormBuilder, ValidationErrors } from '@angular/forms';
import { MatSnackBar } from '@angular/material/snack-bar';

import { LoginService } from '../login.service';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.scss'],
})
export class LoginComponent {
  public errorMessage: string | null = null;
  public loginForm = this.formBuilder.group({
    password: [''],
    username: [''],
  }, { validators: (control: AbstractControl): ValidationErrors | null => {
    const username = control.get('username');
    const password = control.get('password');

    const errors = {
      wrongUsernameType: !(typeof username?.value === "string"),
      wrongPasswordType: !(typeof password?.value === "string"),
      usernameEmpty: username?.value === "",
      passwordEmpty: password?.value === "",
    }

    // Return the entire error object if we encounter any error.
    for (const error of Object.values(errors)) if (error) return errors;

    return null;
   }});

  constructor(
    private formBuilder: FormBuilder,
    private loginService: LoginService,
    private snackBar: MatSnackBar,
    private router: Router,
  ) {}

  async onSubmit(): Promise<void> {
    const { username, password } = this.loginForm.value;
    
    // We need both a valid username and a valid password.
    if (!(username && password) || !this.loginForm.valid) return;
    
    this.loginService.login({ username, password }).subscribe({
      next: () => {
        this.errorMessage = null;
        this.router.navigate(['/']);
      },
      error: () => {
        this.snackBar.open("Failed to log in. Please check your username and password.", "Close", {
          duration: 5000,
        });
      }
    });
  }
}
