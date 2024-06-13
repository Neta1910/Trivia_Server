import { Hourglass } from "react-loader-spinner";

const Loader = () => {
return (
  <Hourglass
    visible={true}
    height="80"
    width="80"
    ariaLabel="hourglass-loading"
    wrapperStyle={{}}
    wrapperClass=""
    colors={["#06bee1", "#d4a373"]}
  />
)
};

export default Loader;
