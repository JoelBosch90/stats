package com.stats.api;

import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class AuthenticationController {

  @RequestMapping("/api/authenticate")
  public String authenticate() {
    return "Hello world!";
  }
}