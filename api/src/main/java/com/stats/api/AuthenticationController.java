package com.stats.api;

import java.util.Map;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServletRequest;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class AuthenticationController {
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
