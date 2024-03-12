package com.stats.api;

import java.util.Map;
import java.util.logging.Logger;
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
  private static final Logger LOGGER = Logger.getLogger(AuthenticationController.class.getName());
  private final CsrfTokenRepository csrfTokenRepository;

  @Autowired
  public AuthenticationController(@Lazy CsrfTokenRepository csrfTokenRepository) {
    this.csrfTokenRepository = csrfTokenRepository;
  }

  @PostMapping(value = "/login", produces = "text/plain")
  public ResponseEntity<String> login(@RequestBody Map<String, String> payload, HttpServletRequest request) {
    LOGGER.info("This is a debug message");

    return new ResponseEntity<String>("happy", HttpStatus.OK);

    // String username = payload.get("username");
    // String password = payload.get("password");

    // // Should log out the previous session before creating a new one.
    // if (request.getUserPrincipal() != null)
    // try {
    // request.logout();
    // } catch (ServletException exception) {
    // return new ResponseEntity<String>("Already logged in.",
    // HttpStatus.BAD_REQUEST);
    // }

    // try {
    // request.login(username, password);
    // } catch (ServletException exception) {
    // return new ResponseEntity<String>("Username and password do not match.",
    // HttpStatus.UNAUTHORIZED);
    // }

    // return new ResponseEntity<String>("Login successful.", HttpStatus.OK);
  }

  @PostMapping(value = "/logout", produces = "text/plain")
  public ResponseEntity<String> logout(HttpServletRequest request) {
    LOGGER.info("This is a debug message");

    return new ResponseEntity<String>("happy", HttpStatus.OK);
    // try {
    // request.logout();
    // } catch (ServletException exception) {
    // // This is an odd scenario that probably shouldn't happen as either the user
    // is
    // // logged in and can be logged out,
    // // or the user is not logged in and thus cannot reach this endpoint.
    // return "Logout unsuccessful.";
    // }

    // return "Logout successful.";
  }

  @GetMapping("/csrf")
  public void csrf(HttpServletRequest request, HttpServletResponse response) {
    // Generate a new CSRF token for this session on the server.
    CsrfToken token = csrfTokenRepository.generateToken(request);
    csrfTokenRepository.saveToken(token, request, response);
  }
}
