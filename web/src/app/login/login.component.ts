import { Component } from '@angular/core';
import { FormBuilder } from '@angular/forms';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.scss']
})
export class LoginComponent {
  loginForm = this.formBuilder.group({
    userName: '',
    password: ''
  });

  constructor(private formBuilder: FormBuilder) {}

  onSubmit(): void {
    console.log('Submit!');
  }
}