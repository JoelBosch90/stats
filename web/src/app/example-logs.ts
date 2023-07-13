export interface LogRow {
  id: number;
  remote_address: string;
  remote_user?: string;
  local_time: string;
  timezone: string;
  http_request_method: string;
  http_request_path: string;
  http_request_query?: string;
  http_request_fragment?: string;
  http_request_version?: string;
  http_status_code: string;
  bytes_sent: string;
  referrer_protocol: string;
  referrer_authentication?: string;
  referrer_domain: string;
  referrer_port?: string;
  referrer_query?: string;
  referrer_fragment?: string;
  browser_name?: string;
  browser_version?: string;
  rendering_engine_name?: string;
  rendering_engine_version?: string;
  operating_system?: string;
  device_type?: string;
}

export const logRows = [
  {
    id: 1,
    operating_system: "Windows",
    remote_address: "172.21.0.1",
    local_time: "22/Jan/2023:14:11:17",
    timezone: "+0000",
    http_request_method: "GET",
    http_request_path: "/build/bundle.css",
    http_request_query: "",
    http_request_fragment: "",
    http_request_version: "1.1",
    http_status_code: "304",
    bytes_sent: "0",
    referrer_protocol: "http",
    referrer_authentication: "",
    referrer_domain: "localhost",
    referrer_port: "8009",
    referrer_query: "",
    referrer_fragment: "",
    browser_name: "Firefox",
    browser_version: "110.0"
  },
  {
    id: 2,
    operating_system: "Windows",
    remote_address: "172.21.0.1",
    local_time: "22/Jan/2023:14:11:15",
    timezone: "+0000",
    http_request_method: "GET",
    http_request_path: "/",
    http_request_version: "1.1",
    http_status_code: "200",
    bytes_sent: "8",
    referrer_protocol: "http",
    referrer_domain: "localhost",
    referrer_port: "8009",
    browser_name: "Firefox",
    browser_version: "110.0"
  },
  {
    id: 3,
    operating_system: "MacOS",
    remote_address: "172.23.2.4",
    local_time: "22/Jan/2023:14:09:03",
    timezone: "+0001",
    http_request_method: "GET",
    http_request_path: "/login",
    http_request_version: "1.1",
    http_status_code: "200",
    bytes_sent: "8",
    referrer_protocol: "https",
    referrer_domain: "localhost",
    referrer_port: "8010",
    browser_name: "Firefox",
    browser_version: "110.0"
  }
]