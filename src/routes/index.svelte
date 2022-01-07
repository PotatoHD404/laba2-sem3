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

  // const vizRenderStringSync = import('@aduh95/viz.js/sync');
  // import LabWorker from '../../scripts/actual-service-worker.js?url';
  import LabWorker1 from '../../scripts/actual-service-worker.js?worker';
  import { onMount } from 'svelte';


  let worker;
  let ok = false;
  let consoleText = '';
  let type_selected = false;
  let prev = 'o';


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


    // const graphviz1 = graphviz('#graph').renderDot(dots[0]);
    // console.log('initialized');
  });


  // fetchWorker.onmessage = ({ data: { status, data } }) => {
  //   if (status) loadState.status = status;
  //   if (data) dataParsed = data;
  //   if (status && status === "done") fetchWorker.terminate();
  // };

  // worker.postMessage('init');
  let n = 0;
  let initialized = false;
  let result;
  let field = [];

  function Command(input, choice) {

    if (ok) {

      let message;
      console.log(input);
      switch (input) {

        case 'init':
          if (choice !== '' && choice - 0 >= 3) {
            n = choice - 0;
          }
          field = new Array(n);
          for (let i = 0; i < n; i++) {
            field[i] = new Array(n);
            for (let j = 0; j < n; j++)
              field[i][j] = '';
          }
          message = '';
          if (initialized)
            message += '-1 -1\n';
          message += '1' + '\n' + choice + '\n';
          worker.postMessage(message);
          initialized = true;
          ok = false;
          prev = 'o';

          break;
        case 'move':
          if (field[choice[0]][choice[1]] === '' && prev !== 'x') {
            ok = false;
            field[choice[0]][choice[1]] = 'x';
            worker.postMessage(`${choice[0]} ${choice[1]} \n`);
            prev = 'x';
          }
          break;
      }
    }
  }

  function print(data) {
    ok = true;
    // console.log(data);

    if (data.includes('Xs won!')) {
      prev = 'x';
      result = 'Xs won!';
      initialized = false;
    } else if (data.includes('Os won!')) {
      prev = 'x';
      result = 'Os won!';
      initialized = false;

    } else if (data.includes('Draw...')) {
      prev = 'x';
      result = 'Draw...';
      initialized = false;

    } else if (data.includes('AI move: ')) {
      // console.log(data);
      prev = 'o';
      result = data.split('AI move: ')[1];
      const move = data.split('AI move: ')[1].split(', ');
      field[move[0] - 0][move[1] - 0] = 'o';
    }

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
        <Input text='Field size' command={(choice)=>{Command('init',choice);}}
               button_text='Set' />
        <Field label_text='Result' text={result} />

        <div class='w-full flex flex-wrap h-full justify-center field'>
          {#each Array(n) as _, i}
            <div class='w-full flex h-auto justify-center'>
              {#each Array(n) as _, j}
                <Button button_text={field[i][j]} command={()=>{Command('move', [i,j])}} />
              {/each}
            </div>

          {/each}
        </div>
        <!--        <Input text='Edges count' command={(choice)=>{Command('remove',choice);}}-->
        <!--               bind:choice={inputValue[1]} />-->
        <!--        <Select text='Directed' command={(choice)=>{Command('init',choice);}}-->
        <!--                options={['True', 'False']} bind:choice={inputValue[2]} />-->
        <!--        <Select text='Edge weighted' command={()=>{Command('init');}}-->
        <!--                button_text='Init' options={['True', 'False']} bind:choice={inputValue[3]} />-->
        <!--        <div class='flex justify-center flex-wrap md:w-2/3 w-full'>-->
        <!--          <Button button_text='Colorize' command={()=>{Command('colorize');}} />-->
        <!--          <Button button_text='Topological sort' command={(choice)=>{Command('top',choice);}} />-->
        <!--          <Button button_text='Add node' command={(choice)=>{Command('add',choice);}} />-->
        <!--        </div>-->
        <!--        <Input text='From node index' command={(choice)=>{Command('remove',choice);}}-->
        <!--               bind:choice={inputValue[4]} />-->
        <!--        <Input text='To node index' command={()=>{Command('dijkstra');}}-->
        <!--               button_text='Dijkstra' bind:choice={inputValue[5]} />-->
        <!--        <Input text='Node index' command={(choice)=>{Command('input',choice);}}-->
        <!--               button_text='Remove' />-->
        <!--        <Field label_text='Result' text={result} />-->
        <!--        <Canvas label_text='Graph' bind:svg={svg} />-->
      </div>
    </div>


  </div>
</div>


<style>
    /*.greenBox {*/
    /*    background-color: rgba(0, 255, 0, 0.2);*/
    /*}*/
    .field {
        width: 40rem;
        height: 40rem;
        font-size: 1.5rem;
    }

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

