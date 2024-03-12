package com.stats.api;

import jakarta.servlet.FilterChain;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.Cookie;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import org.springframework.security.web.csrf.CsrfToken;
import org.springframework.web.filter.OncePerRequestFilter;
import org.springframework.web.util.WebUtils;
import org.springframework.lang.NonNull;

import java.io.IOException;

public class CustomCsrfCookieFilter extends OncePerRequestFilter {

  @Override
  protected void doFilterInternal(@NonNull HttpServletRequest request, @NonNull HttpServletResponse response,
      @NonNull FilterChain filterChain)
      throws ServletException, IOException {
    CsrfToken csrfToken = (CsrfToken) request.getAttribute(CsrfToken.class.getName());
    String token = csrfToken.getToken();

    // If we don't have CSRF token, we can just continue with the request. If
    // the CSRF token is required, the request will fail later on.
    if (csrfToken == null || token == null) {
      filterChain.doFilter(request, response);
      return;
    }

    Cookie cookie = WebUtils.getCookie(request, "XSRF-TOKEN");

    if (cookie == null || !token.equals(cookie.getValue())) {
      cookie = new Cookie("XSRF-TOKEN", token);
      cookie.setPath("/");
      response.addCookie(cookie);
    }

    filterChain.doFilter(request, response);
  }
}
