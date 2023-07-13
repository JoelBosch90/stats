import { Component } from '@angular/core';

import { LogRow, logRows } from '../example-logs';

interface TableRow {
  time: string;
  ip: string;
  method: string;
  page: string;
  domain: string;
}

@Component({
  selector: 'app-logs',
  templateUrl: './logs.component.html',
  styleUrls: ['./logs.component.scss']
})
export class LogsComponent {
  displayedColumns: string[] = ['time', 'ip', 'method', 'page', 'domain'];
  dataSource: TableRow[] = [...logRows].map((logRow: LogRow) => ({
    time: logRow.local_time,
    ip: logRow.remote_address,
    method: logRow.http_request_method,
    page: logRow.http_request_path,
    domain: logRow.referrer_domain
  }));
}
