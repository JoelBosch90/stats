package com.stats.api;

import java.util.Map;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Lazy;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.security.web.csrf.CsrfToken;
import org.springframework.security.web.csrf.CsrfTokenRepository;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class AuthenticationController {
  private final CsrfTokenRepository csrfTokenRepository;

  @Autowired
  public AuthenticationController(@Lazy CsrfTokenRepository csrfTokenRepository) {
    this.csrfTokenRepository = csrfTokenRepository;
  }

  @PostMapping(value = "/login", produces = "text/plain")
  public ResponseEntity<String> login(@RequestBody Map<String, String> payload, HttpServletRequest request) {
    String username = payload.get("username");
    String password = payload.get("password");

    // Should log out the previous session before creating a new one.
    if (request.getUserPrincipal() != null) {
      try {
        request.logout();
      } catch (ServletException exception) {
        return new ResponseEntity<String>("Already logged in and cannot be logged out.",
            HttpStatus.INTERNAL_SERVER_ERROR);
      }
    }

    try {
      request.login(username, password);
    } catch (ServletException exception) {
      return new ResponseEntity<String>("Username and password do not match.", HttpStatus.UNAUTHORIZED);
    }

    return new ResponseEntity<String>("Login successful.", HttpStatus.OK);
  }

  @PostMapping(value = "/logout", produces = "text/plain")
  public ResponseEntity<String> logout(HttpServletRequest request) {
    try {
      request.logout();
      return new ResponseEntity<String>("Logout successful.", HttpStatus.OK);

    } catch (ServletException exception) {
      return new ResponseEntity<String>("Logout unsuccessful.", HttpStatus.INTERNAL_SERVER_ERROR);
    }
  }
}
