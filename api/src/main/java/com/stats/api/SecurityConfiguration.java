package com.stats.api;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.security.config.Customizer;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.core.userdetails.User;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.security.provisioning.InMemoryUserDetailsManager;
import org.springframework.security.web.DefaultSecurityFilterChain;

@Configuration
public class SecurityConfiguration {

  @Bean
  public DefaultSecurityFilterChain filterChain(HttpSecurity http) throws Exception {
    final String EXPECTED_ORIGIN = System.getenv("EXPECTED_ORIGIN");

    return http
      .authorizeHttpRequests((requests) -> requests.anyRequest().authenticated())
      .httpBasic(Customizer.withDefaults())
      .formLogin((formLogin) ->
        formLogin
          .usernameParameter("username")
          .passwordParameter("password")
          .loginPage(String.format("%1$s/login", EXPECTED_ORIGIN))
          .failureUrl(String.format("%1$s/login?failed", EXPECTED_ORIGIN))
          .loginProcessingUrl("/authenticate")
      ).build();
  }

//  @Bean
//  public PasswordEncoder passwordEncoder() {
//    return new BCryptPasswordEncoder();
//  }

  @Bean
  public InMemoryUserDetailsManager userDetailsService() {
    UserDetails user = User.withDefaultPasswordEncoder()
      .username(System.getenv("SUPERUSER_NAME"))
      .password(System.getenv("SUPERUSER_PASSWORD"))
      .build();

    return new InMemoryUserDetailsManager(user);
  }
}
