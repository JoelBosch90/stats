package com.stats.api;

import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import jakarta.servlet.http.HttpServletResponse;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.http.HttpStatus;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.configuration.EnableWebSecurity;
import org.springframework.security.config.http.SessionCreationPolicy;
import org.springframework.security.web.SecurityFilterChain;
import org.springframework.security.web.authentication.HttpStatusEntryPoint;
import org.springframework.security.web.csrf.CookieCsrfTokenRepository;
import org.springframework.security.web.csrf.CsrfTokenRepository;
import org.springframework.security.web.csrf.CsrfTokenRequestAttributeHandler;

@Configuration
@EnableWebSecurity
public class SecurityConfiguration {
  private static final List<String> PUBLIC_ENDPOINTS = List.of("/login", "/logout");
  private static final List<String> XSRF_EXCLUDED = Stream
      .concat(PUBLIC_ENDPOINTS.stream(), List.of("/ws").stream()).collect(Collectors.toList());

  @Bean
  static public CsrfTokenRepository csrfTokenRepository() {
    CookieCsrfTokenRepository repository = CookieCsrfTokenRepository.withHttpOnlyFalse();
    repository.setCookiePath("/");
    return repository;
  }

  @Bean
  static public CsrfTokenRequestAttributeHandler csrfRequestAttributeHandler() {
    CsrfTokenRequestAttributeHandler csrfRequestHandler = new CsrfTokenRequestAttributeHandler();

    // We won't be using the attribute at all, so we have to explicitly disable
    // it. See: https://stackoverflow.com/a/75920811/9978332 for reference.
    csrfRequestHandler.setCsrfRequestAttributeName(null);
    return csrfRequestHandler;
  }

  @Bean
  static public SecurityFilterChain securityFilterChain(HttpSecurity http) throws Exception {
    // Enable CSRF protection for all requests.
    http.csrf(csrf -> csrf
        .ignoringRequestMatchers(XSRF_EXCLUDED.toArray(new String[0]))
        .csrfTokenRepository(SecurityConfiguration.csrfTokenRepository())
        .csrfTokenRequestHandler(SecurityConfiguration.csrfRequestAttributeHandler()));

    // Allow public endpoints to be accessed without authentication.
    http.authorizeHttpRequests(registry -> {
      registry.requestMatchers(PUBLIC_ENDPOINTS.toArray(new String[0])).permitAll();
      registry.anyRequest().authenticated();
    });

    // Make sure that we don't get the default logout redirects.
    http.logout(logout -> logout.permitAll()
        .logoutSuccessHandler((request, response, authentication) -> {
          response.setStatus(HttpServletResponse.SC_OK);
        })
        .deleteCookies("JSESSIONID")
        .invalidateHttpSession(true)
        .clearAuthentication(true));

    // Enable session management.
    http.sessionManagement(session -> session
        .sessionCreationPolicy(SessionCreationPolicy.IF_REQUIRED)
        .sessionFixation(sessionFixation -> sessionFixation.changeSessionId())
        .maximumSessions(1));

    // Send unauthenticated users a Forbidden HTTP response code by default.
    http.exceptionHandling(
        customizer -> customizer.authenticationEntryPoint(new HttpStatusEntryPoint(HttpStatus.FORBIDDEN)));

    return http.build();
  }
}
