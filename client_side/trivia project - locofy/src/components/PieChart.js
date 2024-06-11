import styles from "./PieChart.module.css";
import { Pie } from "react-chartjs-2";
import { Chart, ArcElement, Tooltip, Legend } from 'chart.js';

// Register Chart.js components
Chart.register(ArcElement, Tooltip, Legend);

const PieChart = ({ correctAns, wrongAns }) => {
  const data = {
    labels: ["Correct", "Wrong"],
    datasets: [
      {
        label: "Your answers",
        data: [correctAns, wrongAns],
        backgroundColor: [
          "rgba(255, 99, 132, 0.2)",
          "rgba(54, 162, 235, 0.2)",
        ],
        borderColor: [
          "rgba(255, 99, 132, 1)",
          "rgba(54, 162, 235, 1)",
        ],
        borderWidth: 1,
      },
    ],
  };

  return (
  <div className={styles.frameWrapper}>
    <Pie data={data} />
  </div>);
};

export default PieChart;
