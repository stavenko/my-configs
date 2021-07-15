export const css =`
  bottom: 0;
  right: 0;
  height: 30px;
  background-color:white;
  .flex{
    display: flex;
    flex-direction: row;
  }


  h1 {
    font-size: 30px;
    margin: 16px 0 8px;
  }

  .box {
    width: 30px;
    height: 30px;
    text-align: center;
    vertical-align: middle;
    font-size: 19pt
  }

  .selected-box {
    width: 30px;
    height: 30px;
    text-align: center;
    vertical-align: middle;
    font-size: 19pt;
    background-color: red;
    color: white
  }

  em {
    font-weight: 400;
    font-style: normal;
  }
`
export const spaceMap = {
  'one': 1,
  'two': 2,
  'three': 3,
  'four': 4,
  'five': 5,
  'six': 6,
  'seven': 7,
  'eight': 8,
  'nine': 9,
  'ten': 10,
}

/*
export const widget = ({space}) => {
     if (space.visible) {
        return (<div className="selected-box" key={idx}> {spaceMap[space.label]} </div>)
     } else {
        return (<div className="box" key={idx}> {spaceMap[space.label]} </div>)
     }
}
*/
