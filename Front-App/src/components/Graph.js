import React from "react";
import { Line } from "react-chartjs-2";
import styles from "./styles.module.css";
import { useEffect, useState } from "react";
import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend,
} from "chart.js";

ChartJS.register(
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend
);

function Graph(props) {
  console.log(props.data);
  let label = [];
  props.data.map((myArr, index) => {
    label.push(index);
  });

  return (
    <div className={styles.graph}>
      <Line
        data={{
          /*  labels: props.data.map((x, index) => index), */
          labels: label,

          datasets: [
            {
              data: props.data,
              borderColor: "#000000",
              label: props.tittle,
              backgroundColor: "#000000",
            },
          ],
        }}
        options={{
          plugins: {
            title: {
              display: true,
              text: props.tittle,
              color: "#000000",
              font: {
                size: 35,
              },
            },
          },
          scales: {
            x: {
              grid: {
                color: "#8c8a85",
              },
              ticks: {
                color: "#000000",
              },
              display: true,
              title: {
                display: true,
                text: "Time",
                color: "#000000",
                font: {
                  size: 25,
                },
              },
            },
            y: {
              grid: {
                color: "#8c8a85",
              },

              display: true,
              ticks: {
                color: "#000000",
              },
              title: {
                display: true,
                text: props.tittle,
                color: "#000000",
                font: {
                  size: 25,
                },
              },
            },
          },
        }}
        yAxisSuffix="C"
        yAxisInterval={1} // optional, defaults to 1
      />
    </div>
  );
}

export default Graph;
