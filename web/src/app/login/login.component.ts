import { Component } from '@angular/core';
import { AbstractControl, FormBuilder, ValidationErrors } from '@angular/forms';

import { LoginService } from '../login.service';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.scss'],
})
export class LoginComponent {
  loginForm = this.formBuilder.group({
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
  ) {}

  onSubmit(): void {
    const { username, password } = this.loginForm.value;
    
    if (username && password) this.loginService.authenticate({ username, password });
  }
}
