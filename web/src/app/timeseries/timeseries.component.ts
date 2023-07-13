import { Component } from '@angular/core';

import { TimeseriesRow, timeseries } from '../example-timeseries';

@Component({
  selector: 'app-timeseries',
  templateUrl: './timeseries.component.html',
  styleUrls: ['./timeseries.component.scss']
})
export class TimeseriesComponent {
  displayedColumns: string[] = ['timestamp', 'amount'];
  tableData = [...timeseries];
  chartData = [{
    name: "Page views",
    series: timeseries.map(({ timestamp, amount }) => ({ name: timestamp, value: amount }))
  }];

  view: [number, number] = [800, 400];
  legend: boolean = true;
  showLabels: boolean = true;
  animations: boolean = true;
  xAxis: boolean = true;
  yAxis: boolean = true;
  xAxisLabel: string = 'Date';
  yAxisLabel: string = 'Amount';
  showYAxisLabel: boolean = true;
  showXAxisLabel: boolean = true;

  constructor() {}
}
