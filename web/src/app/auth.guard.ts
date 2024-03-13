import { CanActivateChildFn, Router } from '@angular/router';
import { inject } from '@angular/core';
import { DataService } from './data.service'; 

const PUBLIC_ROUTES = [ "/login" ];

export const authGuard: CanActivateChildFn = (route, state) => {
  const dataService = inject(DataService);
  const router = inject(Router);

  const isAllowed = PUBLIC_ROUTES.includes(state.url) || dataService.get('loggedIn');
  if (!isAllowed) router.navigate(["/login"]);

  return isAllowed;
};

