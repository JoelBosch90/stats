package com.stats.api;

import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServletRequest;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

import java.util.Map;
import java.util.Objects;

@RestController
public class AuthenticationController {
  @PostMapping("/login")
  public boolean login(@RequestBody Map<String, String> payload, HttpServletRequest request) {
    try {
      request.login(payload.get("username"), payload.get("password"));
    } catch (ServletException exception) {
      throw new RuntimeException("Invalid credentials");
    }

    request.getUserPrincipal();

    return true;
  }
}
