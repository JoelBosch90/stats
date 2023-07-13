import { Component } from '@angular/core';

import { TimeseriesRow, timeseries } from '../example-timeseries';

@Component({
  selector: 'app-timeseries',
  templateUrl: './timeseries.component.html',
  styleUrls: ['./timeseries.component.scss']
})
export class TimeseriesComponent {
  displayedColumns: string[] = ['timestamp', 'amount'];
  dataSource = [...timeseries];
}
