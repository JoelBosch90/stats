package com.stats.api;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class AuthenticationController {

  @GetMapping("/authenticate")
  public String authenticate() {
    return "Hello world!11!!3";
  }
}