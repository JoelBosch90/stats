package com.stats.api;

import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServletRequest;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.security.web.csrf.CsrfToken;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

import java.util.Map;

@RestController
public class AuthenticationController {
  @PostMapping(value ="/login", produces = "text/plain")
  public ResponseEntity<String> login(@RequestBody Map<String, String> payload, HttpServletRequest request) {
    String username = payload.get("username");
    String password = payload.get("password");

    // Should log out the previous session before creating a new one.
    if (request.getUserPrincipal() != null) try {
      request.logout();
    } catch (ServletException exception) {
      return new ResponseEntity<String>("Already logged in.", HttpStatus.BAD_REQUEST);
    }

    try {
      request.login(username, password);
    } catch (ServletException exception) {
      return new ResponseEntity<String>("Username and password do not match.", HttpStatus.UNAUTHORIZED);
    }

    return new ResponseEntity<String>("Login successful.", HttpStatus.OK);
  }

  @PostMapping(value = "/logout", produces = "text/plain")
  public String logout(HttpServletRequest request) {
    try {
      request.logout();
    } catch (ServletException exception) {
      // This is an odd scenario that probably shouldn't happen as either the user is logged in and can be logged out,
      // or the user is not logged in and thus cannot reach this endpoint.
      return "Logout unsuccessful.";
    }

    return "Logout successful.";
  }

  @GetMapping("/csrf")
  public CsrfToken csrf(CsrfToken token) {
    return token;
  }
}
