package com.stats.api;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.http.HttpStatus;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.core.userdetails.User;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.security.provisioning.InMemoryUserDetailsManager;
import org.springframework.security.web.SecurityFilterChain;
import org.springframework.security.web.authentication.HttpStatusEntryPoint;

@Configuration
public class SecurityConfiguration {

  @Bean
  public SecurityFilterChain securityFilterChain(HttpSecurity http) throws Exception {
    return http
      .authorizeHttpRequests((requests) -> requests
        .requestMatchers("/login").permitAll()
        .requestMatchers("/**").authenticated()
        .anyRequest().denyAll())
      .exceptionHandling(customizer -> customizer.authenticationEntryPoint(new HttpStatusEntryPoint(HttpStatus.UNAUTHORIZED)))
      .csrf().disable()
      .build();
  }

//  @Bean
//  public PasswordEncoder passwordEncoder() {
//    return new BCryptPasswordEncoder();
//  }
//
//  @Bean
//  public InMemoryUserDetailsManager userDetailsService() {
//    UserDetails user = User.withDefaultPasswordEncoder()
//      .username(System.getenv("SUPERUSER_NAME"))
//      .password(System.getenv("SUPERUSER_PASSWORD"))
//      .build();
//
//    return new InMemoryUserDetailsManager(user);
//  }
}
