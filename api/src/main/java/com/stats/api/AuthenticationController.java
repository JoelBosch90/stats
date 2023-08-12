package com.stats.api;

import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServletRequest;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

import java.util.Map;

@RestController
public class AuthenticationController {
  @PostMapping("/login")
  public ResponseEntity<String> login(@RequestBody Map<String, String> payload, HttpServletRequest request) throws RuntimeException {
    try {
      request.login(payload.get("username"), payload.get("password"));
    } catch (ServletException exception) {
      return new ResponseEntity<String>("Username and password do not match.", HttpStatus.UNAUTHORIZED);
    }

    return new ResponseEntity<String>("Login successful.", HttpStatus.OK);
  }

  @PostMapping("/logout")
  public ResponseEntity<String> logout(HttpServletRequest request) throws RuntimeException {
    try {
      request.logout();
    } catch (ServletException exception) {
      // This is an odd scenario that probably shouldn't happen as either the user is logged in and can be logged out,
      // or the user is not logged in and thus cannot reach this endpoint.
      return new ResponseEntity<String>("Logout unsuccessful.", HttpStatus.OK);
    }

    return new ResponseEntity<String>("Logout successful.", HttpStatus.OK);
  }
}
