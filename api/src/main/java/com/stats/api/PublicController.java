package com.stats.api;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class PublicController {

  @GetMapping("/public")
  public String getPublic() {
    return "Anyone sees this.";
  }
}
