export interface TimeseriesRow {
  timestamp: string;
  amount: number;
}

export const timeseries: TimeseriesRow[] = [
  {
    timestamp: "19/Jan/2023",
    amount: 100,
  },
  {
    timestamp: "20/Jan/2023",
    amount: 109,
  },
  {
    timestamp: "21/Jan/2023",
    amount: 131,
  },
  {
    timestamp: "22/Jan/2023",
    amount: 116,
  },
]