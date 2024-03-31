package com.stats.api;

import java.util.Map;
import jakarta.servlet.http.HttpSession;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.http.server.ServerHttpRequest;
import org.springframework.http.server.ServerHttpResponse;
import org.springframework.http.server.ServletServerHttpRequest;
import org.springframework.lang.NonNull;
import org.springframework.lang.Nullable;
import org.springframework.web.socket.WebSocketHandler;
import org.springframework.web.socket.config.annotation.EnableWebSocket;
import org.springframework.web.socket.config.annotation.WebSocketConfigurer;
import org.springframework.web.socket.config.annotation.WebSocketHandlerRegistry;
import org.springframework.web.socket.server.HandshakeInterceptor;

@Configuration
@EnableWebSocket
public class WebSocketConfiguration implements WebSocketConfigurer {
  @Value("${ORIGIN:}")
  public String currentOrigin;

  @Autowired
  private MessageHandler messageHandler;

  @Override
  public void registerWebSocketHandlers(@NonNull WebSocketHandlerRegistry registry) throws IllegalStateException {
    if (messageHandler != null) {
      registry.addHandler(messageHandler, "/ws")
          .addInterceptors(httpSessionHandshakeInterceptor())
          .setAllowedOrigins(currentOrigin);
    } else {
      throw new IllegalStateException("MessageHandler is not available.");
    }
  }

  @Bean
  public HandshakeInterceptor httpSessionHandshakeInterceptor() {
    return new HandshakeInterceptor() {
      @Override
      public boolean beforeHandshake(@NonNull ServerHttpRequest request, @NonNull ServerHttpResponse response,
          @NonNull WebSocketHandler webSocketHandler, @NonNull Map<String, Object> attributes)
          throws Exception {
        if (!(request instanceof ServletServerHttpRequest)) {
          return true;
        }

        // Get access to the current HTTP session, but don't create a new one.
        HttpSession session = ((ServletServerHttpRequest) request).getServletRequest().getSession(false);

        if (session != null) {
          // Store the HTTP session ID for use in the WebSocket session attributes.
          attributes.put("sessionId", session.getId());
        }

        return true;
      }

      @Override
      public void afterHandshake(@NonNull ServerHttpRequest request, @NonNull ServerHttpResponse response,
          @NonNull WebSocketHandler webSocketHandler, @Nullable Exception exception) {
        // We don't need to do anything specific here, but it is required by the
        // interface that we implement this.
      }
    };
  }
}