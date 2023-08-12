package com.stats.api;

import jakarta.servlet.http.HttpServletResponse;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.http.HttpStatus;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.web.SecurityFilterChain;
import org.springframework.security.web.authentication.HttpStatusEntryPoint;
import org.springframework.security.web.csrf.CookieCsrfTokenRepository;

@Configuration
public class SecurityConfiguration {

  @Bean
  public SecurityFilterChain securityFilterChain(HttpSecurity http) throws Exception {
    return http
      .authorizeHttpRequests((requests) -> requests
        // Only the login endpoint should be publicly accessible.
        .requestMatchers("/login").permitAll()
        .anyRequest().authenticated())
      // Make sure that we don't get the default logout redirects.
      .logout(logout -> logout.permitAll()
        .logoutSuccessHandler((request, response, authentication) -> { response.setStatus(HttpServletResponse.SC_OK); })
      )
      // Send unauthenticated users a Forbidden HTTP response code by default.
      .exceptionHandling(customizer -> customizer.authenticationEntryPoint(new HttpStatusEntryPoint(HttpStatus.FORBIDDEN)))
      .csrf(csrf -> csrf.csrfTokenRepository(CookieCsrfTokenRepository.withHttpOnlyFalse()))
      .build();
  }
}
