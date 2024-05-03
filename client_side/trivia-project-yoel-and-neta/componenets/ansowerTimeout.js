import React, { useEffect, useState } from 'react';
import styles from '../styles/AnswerTimeout.module.css'; // Assuming the CSS module file is named AnswerTimeout.module.css

function AnswerTimeout({ timeout }) {
    const [width, setWidth] = useState(100);

    useEffect(() => {
        setWidth(100); // Reset width to 100% on new timeout
        const interval = setInterval(() => {
            setWidth((prevWidth) => (prevWidth > 0 ? prevWidth - (100 / timeout) : 0));
        }, 1000); // Decrease width based on timeout duration

        return () => clearInterval(interval);
    }, [timeout]);

    return (
        <div className={styles.timeoutWrapper}>
            <div className={styles.timeoutBar} style={{ width: `${width}%` }}></div>
            Answer Timeout: {timeout} seconds
        </div>
    );
}

export default AnswerTimeout;
