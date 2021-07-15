import {css} from './utils';
// This is a simple example Widget to get you started with Übersicht.
// For the full documentation please visit:
// https://github.com/felixhageloh/uebersicht

// You can modify this widget as you see fit, or simply delete this file to
// remove it.

// this is the shell command that gets executed every time this widget refreshes
export const command = "/usr/local/bin/yabai -m query --spaces --display 1"

// the refresh frequency in milliseconds
export const refreshFrequency = 1000;

// the CSS style for this widget, written using Emotion
// https://emotion.sh/
export const className = css
const spaceMap = {
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

// render gets called after the shell command has executed. The command's output
// is passed in as a string.
export const render = ({output}) => {
  const data = JSON.parse(output);

  return (
    <div> 
     {data.map((space, idx) => {
       if (space.visible) {
          return (<div className="selected-box" key={idx}> {spaceMap[space.label]} </div>)
       } else {
          return (<div className="box" key={idx}> {spaceMap[space.label]} </div>)
       }
     })}
    </div>
  );
}

