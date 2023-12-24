import React from "react";
import { useEffect, useState } from "react";
import Graph from "./Graph";
import styles from "./styles.module.css";

function Home() {
  const [toggle, setToggle] = useState(false);
  const [text, setText] = useState("Show Temperature");
  const [graphData, setgraphData] = useState([]);
  const [tittle, setTittle] = useState("Humidity");
  const [delay, setdelay] = useState(0);
  let data;
  let temp = [];
  let Humidity = [];


  const dataURL = "http://127.0.0.1:8000/measures";
  useEffect(() => {
    fetch(dataURL)
      .then((response) => response.json()) // get response, convert to json
      .then((json) => {
        data = json;
        data.map((value) => {
          if(value.measure_type=="temp")
          {
            temp.push(value.measure);
          }
          if(value.measure_type=="hum")
          {
            Humidity.push(value.measure);
          }
        
        });

        setgraphData(toggle ? temp : Humidity);
      })
      .catch((error) => alert(error)); // display errors
  }, [setInterval(()=>{
    setdelay(delay =delay+1);
  },3000)]);
  const toggleHandler = () => {
    setToggle(!toggle);
    setText(toggle ? "Show Temperature" : "Show Humidity");
    setTittle(toggle ? "Humidity" : "Temperature");
  };

  console.log("graphData", graphData);
  

  return (
    <div className={styles.container}>
      <div className={styles.buttondiv}>
        <button className={styles.button} onClick={toggleHandler}>
          {text}
        </button>
      </div>
      <div>
        <div>
          <Graph data={graphData} tittle={tittle} />
        </div>
      </div>
    </div>
  );
}

export default Home;
