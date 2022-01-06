<!--<script type="module">-->

<!--  import dot2svg from '@aduh95/viz.js/async';-->
<!--  // import * as d3 from "https://cdn.skypack.dev/d3@7";-->

<!--  // const div = selectAll("div");-->

<!--</script>-->
<script>
  import Input from '../components/input.svelte';
  import Select from '../components/select.svelte';
  import Field from '../components/field.svelte';
  import Button from '../components/button.svelte';
  import Canvas from '../components/canvas.svelte';
  import Viz from 'viz.js';

  import { Module, render } from 'viz.js/full.render.js';

  // const vizRenderStringSync = import('@aduh95/viz.js/sync');
  // import LabWorker from '../../scripts/actual-service-worker.js?url';
  import LabWorker1 from '../../scripts/actual-service-worker.js?worker';
  import { onMount } from 'svelte';


  let worker;
  let ok = false;
  let consoleText = '';
  let type_selected = false;
  let sequence = '';
  let result = '';
  let inputValue = ['', '', 'True', 'True', '', ''];
  let dots = [];
  let svg = '';
  let text = '';
  let viz = new Viz({ Module, render });

  function render_graph(dot) {
    viz.renderString(dot)
      .then(result => {
        svg = result;
      })
      .catch(error => {
        // Create a new Viz instance (@see Caveats page for more info)
        viz = new Viz({ Module, render });

        // Possibly display the error
        console.error(error);
      });
  }

  function queue() {
    if (dots.length !== 0) {
      console.log();
      const el = dots.shift();
      render_graph(el);

    }
    // console.log(dots.length);
  }

  onMount(async () => {
    // worker = new Worker(LabWorker);
    worker = new LabWorker1();
    worker.onmessage = (e) => {
      if (e && e.data) {
        print(e.data);
      }
    };
    worker.postMessage('init');
    ok = true;
    setInterval(queue, 1000);


    // const graphviz1 = graphviz('#graph').renderDot(dots[0]);
    // console.log('initialized');
  });


  // fetchWorker.onmessage = ({ data: { status, data } }) => {
  //   if (status) loadState.status = status;
  //   if (data) dataParsed = data;
  //   if (status && status === "done") fetchWorker.terminate();
  // };

  // worker.postMessage('init');

  function Command(input, choice) {

    if (ok) {
      ok = false;
      let message;
      switch (input) {

        case 'init':
          // console.log(inputValue);
          message = '1' + '\n';
          if (inputValue[0] === '')
            message += '0';
          else
            message += inputValue[0];
          message += '\n';
          if (inputValue[1] === '')
            message += '0';
          else
            message += inputValue[1];
          message += '\n';
          if (inputValue[2] === 'True')
            message += '1';
          else
            message += '2';
          message += '\n';
          if (inputValue[3] === 'True')
            message += '1';
          else
            message += '2';
          message += '\n' + '9' + '\n';

          worker.postMessage(message);
          break;
        case 'colorize':
          worker.postMessage('8' + '\n');
          break;
        case 'top':
          worker.postMessage('6' + '\n');
          break;
        case 'add':
          worker.postMessage('2' + '\n' + '9' + '\n');
          break;
        case 'remove':
          if (choice !== '')
            worker.postMessage('2' + '\n' + choice + '\n');
          break;
        case 'dijkstra':
          message = '7' + '\n';
          if (inputValue[4] === '')
            message += '0';
          else
            message += inputValue[4];
          message += '\n';
          if (inputValue[5] === '')
            message += '1';
          else
            message += inputValue[5];
          worker.postMessage(message);
          break;
      }
    }
  }

  function print(data) {
    ok = true;
    // console.log(data);
    text += data;
    if (text.includes('graph {') && text.includes('}')) {
      if (text.includes('digraph {'))
        text = 'digraph {' + text.split('digraph {')[1];
      else
        text = 'graph {' + text.split('graph {')[1];
      // console.log(text);
      text.split('}').forEach((el) => {
        if (el.includes('graph {'))
          dots.push(el + '}');
        // console.log(dots);

      });
      text = '';
    }
    if (data.includes('Chromatic num = '))
      result = data.split('Chromatic num = ')[1];
    else if (data.includes('Topological order is'))
      result = data.split('Topological order is')[1];

    consoleText += data + '\r\n';
    let textarea = document.getElementById('consoleOutput');
    let temp = textarea.scrollTop;
    let interval = setInterval(() => {
      let end = textarea.scrollHeight;
      if (temp < end) {
        textarea.scrollTop += 50;
        temp += 50;
      } else {
        clearInterval(interval);
      }
    }, 5);

  }

</script>

<div class='flex justify-center'>
  <div class='flex justify-center md:w-full xl:w-2/3 2xl:w-1/2'>
    <div class='flex justify-center flex-wrap md:w-2/3 w-full'>
    <textarea id='consoleOutput'
              class='px-2 py-2 flex console bg-light ring-1 ring-outline-light dark:bg-deep-black dark:text-gray-300
       rounded-md w-full focus:outline-none h-44 dark:ring-outline-dark m-1'
              readonly>{consoleText}</textarea>


      <div class='my-2 w-full flex flex-wrap justify-center' id='menu'>
        <Input text='Nodes count' command={(choice)=>{Command('input',choice);}}
               bind:choice={inputValue[0]} />
        <Input text='Edges count' command={(choice)=>{Command('remove',choice);}}
               bind:choice={inputValue[1]} />
        <Select text='Directed' command={(choice)=>{Command('init',choice);}}
                options={['True', 'False']} bind:choice={inputValue[2]} />
        <Select text='Edge weighted' command={()=>{Command('init');}}
                button_text='Init' options={['True', 'False']} bind:choice={inputValue[3]} />
        <div class='flex justify-center flex-wrap md:w-2/3 w-full'>
          <Button button_text='Colorize' command={()=>{Command('colorize');}} />
          <Button button_text='Topological sort' command={(choice)=>{Command('top',choice);}} />
          <Button button_text='Add node' command={(choice)=>{Command('add',choice);}} />
        </div>
        <Input text='From node index' command={(choice)=>{Command('remove',choice);}}
               bind:choice={inputValue[4]} />
        <Input text='To node index' command={()=>{Command('dijkstra');}}
               button_text='Dijkstra' bind:choice={inputValue[5]} />
        <Input text='Node index' command={(choice)=>{Command('input',choice);}}
               button_text='Remove' />
        <Field label_text='Result' text={result} />
        <Canvas label_text='Graph' bind:svg={svg} />
      </div>
    </div>


  </div>
</div>


<style>
    /*.greenBox {*/
    /*    background-color: rgba(0, 255, 0, 0.2);*/
    /*}*/

    label {
        top: 0;
        transform: translateY(-100%);
        font-size: 11px;
    }

    :global(body) {
        @apply m-auto transition-colors duration-300 bg-dark;
    }

    :global(body.light) {
        @apply bg-white;
    }

</style>

