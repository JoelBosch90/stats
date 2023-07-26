package com.stats.api;

import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class AuthenticationController {

  @RequestMapping("/authenticate")
  public String authenticate() {
    return "hello world";
  }
}
