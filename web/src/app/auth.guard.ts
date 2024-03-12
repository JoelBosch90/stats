import { CanActivateChildFn, Router } from '@angular/router';
import { inject } from '@angular/core';
import { LoginService } from './login.service'; 

const PUBLIC_ROUTES = [ "/login" ];

export const authGuard: CanActivateChildFn = (route, state) => {
  const loginService = inject(LoginService);
  const router = inject(Router);

  const isAllowed = PUBLIC_ROUTES.includes(state.url) || loginService.isLoggedIn();
  if (!isAllowed) router.navigate(["/login"]);

  return isAllowed;
};

