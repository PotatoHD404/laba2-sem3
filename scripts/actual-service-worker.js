
import Laba3 from './Laba3.js';

function cin(input) {
  if (self.instance?.listening) {
    // const event = new CustomEvent('cin', { input: input });
    self.instance.listening = false;
    self.instance.message(input);
    // self.instance.dispatchEvent(event);
  } else {
    console.log('Not responding to your input. Try again later.');
  }
}

self.onmessage = async (e) => {

  if (e.data === 'init') {

    self.instance = await Laba3({
      'print': (data) => {
        postMessage(data);
      }
    });

    self.instance.listening = false;
    self.instance.start();
  } else {
    cin(e.data);
  }
};