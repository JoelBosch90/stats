package com.stats.api;

import java.io.IOException;
import java.util.List;

import jakarta.servlet.FilterChain;
import jakarta.servlet.FilterConfig;
import jakarta.servlet.ServletException;
import jakarta.servlet.ServletRequest;
import jakarta.servlet.ServletResponse;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import org.springframework.boot.web.servlet.FilterRegistrationBean;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.core.Ordered;
import org.springframework.http.HttpStatus;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.configuration.EnableWebSecurity;
import org.springframework.security.web.SecurityFilterChain;
import org.springframework.security.web.authentication.HttpStatusEntryPoint;
import org.springframework.security.web.csrf.CookieCsrfTokenRepository;
import org.springframework.security.web.csrf.CsrfFilter;
import org.springframework.security.web.csrf.CsrfTokenRepository;

import jakarta.servlet.Filter;

@Configuration
@EnableWebSecurity
public class SecurityConfiguration {
  private static final List<String> PUBLIC_ENDPOINTS = List.of("/login", "/logout", "/csrf", "/public");

  @Bean
  static public CsrfTokenRepository csrfTokenRepository() {
    CookieCsrfTokenRepository repository = CookieCsrfTokenRepository.withHttpOnlyFalse();
    repository.setCookiePath("/");
    repository.setHeaderName("x-xsrf-token");
    return repository;
  }

  @Bean
  public FilterRegistrationBean<Filter> csrfLoggingFilter(CsrfTokenRepository csrfTokenRepository) {
    FilterRegistrationBean<Filter> registrationBean = new FilterRegistrationBean<>();

    Filter filter = new Filter() {
      @Override
      public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain)
          throws IOException, ServletException {
        if (request instanceof HttpServletRequest) {
          HttpServletRequest httpServletRequest = (HttpServletRequest) request;
          String header = httpServletRequest.getHeader("x-xsrf-token");
          System.out.println("X-XSRF-TOKEN before CsrfFilter: " + header);
        }
        chain.doFilter(request, response);
      }

      @Override
      public void init(FilterConfig filterConfig) {
      }

      @Override
      public void destroy() {
      }
    };

    registrationBean.setFilter(filter);
    registrationBean.setOrder(Ordered.HIGHEST_PRECEDENCE); // Set the order to the highest value to make it the last
                                                           // filter before CsrfFilter

    return registrationBean;
  }

  @Bean
  static public SecurityFilterChain securityFilterChain(HttpSecurity http) throws Exception {
    // Enable CSRF protection for all requests.
    http.csrf(csrf -> csrf.csrfTokenRepository(SecurityConfiguration.csrfTokenRepository()));

    http.authorizeHttpRequests(registry -> {
      for (String endpoint : PUBLIC_ENDPOINTS) {
        registry.requestMatchers(endpoint).permitAll();
      }

      registry.anyRequest().authenticated();
    });

    // Make sure that we don't get the default logout redirects.
    // http.logout(logout -> logout.permitAll()
    // .logoutSuccessHandler((request, response, authentication) -> {
    // response.setStatus(HttpServletResponse.SC_OK);
    // })
    // .deleteCookies("JSESSIONID")
    // .invalidateHttpSession(true)
    // .clearAuthentication(true));
    // Send unauthenticated users a Forbidden HTTP response code by default.
    http.exceptionHandling(
        customizer -> customizer.accessDeniedHandler(new LoggingAccessDeniedHandler())
            .authenticationEntryPoint(new HttpStatusEntryPoint(HttpStatus.FORBIDDEN)));

    return http.build();
  }
}
