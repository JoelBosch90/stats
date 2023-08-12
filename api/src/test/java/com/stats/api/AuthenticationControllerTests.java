package com.stats.api;

import com.fasterxml.jackson.databind.ObjectMapper;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.http.MediaType;
import org.springframework.test.web.servlet.MockMvc;

import java.util.HashMap;
import java.util.Map;

import static org.springframework.security.test.web.servlet.request.SecurityMockMvcRequestPostProcessors.csrf;
import static org.springframework.security.test.web.servlet.response.SecurityMockMvcResultMatchers.authenticated;
import static org.springframework.security.test.web.servlet.response.SecurityMockMvcResultMatchers.unauthenticated;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.post;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;

@AutoConfigureMockMvc
// Make sure that we mock the username and password.
@SpringBootTest( properties = {"spring.security.user.name = user", "spring.security.user.password = password"})
public class AuthenticationControllerTests {

  @Autowired
  private MockMvc mockMvc;

  @Autowired
  private ObjectMapper objectMapper;

  @Test
  public void csrfFailure() throws Exception {
    Map<String, Object> body = new HashMap<>();
    body.put("username", "user");
    body.put("password", "password");

    this.mockMvc.perform(post("/login")
        .contentType(MediaType.APPLICATION_JSON)
        .content(objectMapper.writeValueAsString(body)))
      .andExpect(status().isForbidden())
      .andExpect(unauthenticated())
      .andExpect(redirectedUrl(null))
      .andExpect(forwardedUrl(null))
      .andReturn();
  }

  @Test
  public void loginSuccess() throws Exception {
    Map<String, Object> body = new HashMap<>();
    body.put("username", "user");
    body.put("password", "password");

    this.mockMvc.perform(post("/login")
        .contentType(MediaType.APPLICATION_JSON)
        .content(objectMapper.writeValueAsString(body))
        .with(csrf()))
      .andExpect(status().isOk())
      .andExpect(authenticated())
      .andExpect(redirectedUrl(null))
      .andExpect(forwardedUrl(null))
      .andReturn();
  }

  @Test
  public void loginFailure() throws Exception {
    Map<String, Object> body = new HashMap<>();
    body.put("username", "wrongUser");
    body.put("password", "wrongPassword");

    this.mockMvc.perform(post("/login")
        .contentType(MediaType.APPLICATION_JSON)
        .content(objectMapper.writeValueAsString(body))
        .with(csrf()))
      .andExpect(status().isUnauthorized())
      .andExpect(unauthenticated())
      .andExpect(redirectedUrl(null))
      .andExpect(forwardedUrl(null))
      .andReturn();
  }

  @Test
  public void logoutSuccess() throws Exception {
    this.mockMvc.perform(post("/logout").with(csrf()))
      .andExpect(status().isOk())
      .andExpect(unauthenticated())
      .andExpect(redirectedUrl(null))
      .andExpect(forwardedUrl(null))
      .andReturn();
  }
}
