import HighhScoreres1 from "../components/HighhScoreres1";
import FrameComponent3 from "../components/FrameComponent3";
import styles from "./Statistics.module.css";

const Statistics = () => {
  return (
    <div className={styles.statistics}>
      <section className={styles.highhScoreresParent}>
        <HighhScoreres1 />
        <div className={styles.frameWrapper}>
          <div className={styles.vectorParent}>
            <img
              className={styles.frameChild}
              loading="lazy"
              alt=""
              src="/ellipse-3.svg"
            />
            <div className={styles.rectangleParent}>
              <div className={styles.frameItem} />
              <div className={styles.pieChartWould}>
                Pie chart (would be added in react)
              </div>
            </div>
          </div>
        </div>
      </section>
      <FrameComponent3 />
    </div>
  );
};

export default Statistics;
