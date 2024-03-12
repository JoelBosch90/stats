package com.stats.api;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import java.io.IOException;
import jakarta.servlet.ServletException;
import org.springframework.security.web.access.AccessDeniedHandlerImpl;
import org.springframework.security.web.csrf.CsrfToken;
import org.springframework.security.web.csrf.CsrfTokenRepository;
import org.springframework.security.web.csrf.CsrfTokenRequestHandler;
import org.springframework.security.web.csrf.DeferredCsrfToken;
import org.springframework.security.web.csrf.XorCsrfTokenRequestAttributeHandler;
import org.springframework.util.Assert;
import org.springframework.security.access.AccessDeniedException;
import org.springframework.security.crypto.codec.Utf8;
import org.springframework.security.web.access.AccessDeniedHandler;
import java.util.Enumeration;
import jakarta.servlet.http.Cookie;
import java.security.MessageDigest;
import java.util.Base64;

public class LoggingAccessDeniedHandler implements AccessDeniedHandler {

    private static final Logger log = LoggerFactory.getLogger(LoggingAccessDeniedHandler.class);

    /**
     * Constant time comparison to prevent against timing attacks.
     * 
     * @param expected
     * @param actual
     * @return
     */
    private static boolean equalsConstantTime(String expected, String actual) {
        if (expected == actual) {
            return true;
        }
        if (expected == null || actual == null) {
            return false;
        }
        // Encode after ensure that the string is not null
        byte[] expectedBytes = Utf8.encode(expected);
        byte[] actualBytes = Utf8.encode(actual);
        return MessageDigest.isEqual(expectedBytes, actualBytes);
    }

    private String fakeResolveCsrfTokenValue(HttpServletRequest request, CsrfToken csrfToken) {
        Assert.notNull(request, "request cannot be null");
        Assert.notNull(csrfToken, "csrfToken cannot be null");
        String actualToken = request.getHeader(csrfToken.getHeaderName());
        if (actualToken == null) {
            actualToken = request.getParameter(csrfToken.getParameterName());
        }
        return actualToken;
    }

    private static String getTokenValue(String actualToken, String token) {
        byte[] actualBytes;
        try {
            actualBytes = Base64.getUrlDecoder().decode(actualToken);
        } catch (Exception ex) {
            return null;
        }
        byte[] tokenBytes = Utf8.encode(token);
        int tokenSize = tokenBytes.length;
        log.error("Actual bytes: " + actualBytes.length + " bytes");
        log.error("Token length: " + tokenSize + " chars");
        if (actualBytes.length < tokenSize) {
            return null;
        }

        // extract token and random bytes
        int randomBytesSize = actualBytes.length - tokenSize;
        byte[] xoredCsrf = new byte[tokenSize];
        byte[] randomBytes = new byte[randomBytesSize];

        System.arraycopy(actualBytes, 0, randomBytes, 0, randomBytesSize);
        System.arraycopy(actualBytes, randomBytesSize, xoredCsrf, 0, tokenSize);

        byte[] csrfBytes = xorCsrf(randomBytes, xoredCsrf);
        return (csrfBytes != null) ? Utf8.decode(csrfBytes) : null;
    }

    private static byte[] xorCsrf(byte[] randomBytes, byte[] csrfBytes) {
        if (csrfBytes.length < randomBytes.length) {
            return null;
        }
        int len = Math.min(randomBytes.length, csrfBytes.length);
        byte[] xoredCsrf = new byte[len];
        System.arraycopy(csrfBytes, 0, xoredCsrf, 0, csrfBytes.length);
        for (int i = 0; i < len; i++) {
            xoredCsrf[i] ^= randomBytes[i];
        }
        return xoredCsrf;
    }

    @Override
    public void handle(HttpServletRequest request, HttpServletResponse response,
            AccessDeniedException accessDeniedException) throws IOException, ServletException {

        CsrfTokenRepository tokenRepository = SecurityConfiguration.csrfTokenRepository();
        DeferredCsrfToken deferredCsrfToken = tokenRepository.loadDeferredToken(request, response);
        CsrfTokenRequestHandler requestHandler = new XorCsrfTokenRequestAttributeHandler();

        CsrfToken csrfToken = deferredCsrfToken.get();
        log.error("Deferred token: " + csrfToken.getToken());
        log.error("Deferred token header name: " + csrfToken.getHeaderName());
        String aToken = request.getHeader(csrfToken.getHeaderName());
        log.error("Actual token w/ header name: " + aToken);

        String fakeToken = fakeResolveCsrfTokenValue(request, csrfToken);
        log.error("Fake csrf token: " + fakeToken);
        String convertedToken = getTokenValue(fakeToken, csrfToken.getToken());
        log.error("Converted token: " + convertedToken);

        String actualToken = requestHandler.resolveCsrfTokenValue(request, csrfToken);
        log.error("Actual csrf token: " + actualToken);
        log.error("Comparison: " + equalsConstantTime(csrfToken.getToken(), actualToken));

        // delegate to the default AccessDeniedHandler
        new AccessDeniedHandlerImpl().handle(request, response, accessDeniedException);
    }
}