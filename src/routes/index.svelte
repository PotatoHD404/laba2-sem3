<script>
  import Input from '../components/input.svelte';
  import Select from '../components/select.svelte';
  import Field from '../components/field.svelte';
  import LabWorker from '../../scripts/service-worker.js?url';
  // import LabWorker1 from '../../static/scripts/actual-service-worker.js?worker';
  import { onMount } from 'svelte';

  let worker;
  let ok = false;
  let consoleText = '';
  let type_selected = false;
  let sequence = '';
  let result = '';
  onMount(async () => {
    worker = new Worker(LabWorker);
    // worker = new LabWorker1();
    worker.onmessage = (e) => {
      if (e && e.data) {
        print(e.data);
      }
    };
    worker.postMessage('init');
    ok = true;
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
      switch (input) {
        case 'type':
          choice = choice.replace(/\s/g, '');
          // console.log(choice);
          switch (choice) {
            case 'int':
              choice = '1';
              break;
            case 'float':
              choice = '2';
              break;
            case 'string':
              choice = '3';
              break;
            case 'complex':
              choice = '4';
              break;
          }
          // const char *MSGS[] = {"0. Quit",
          // "1. Int",
          // "2. Float",
          // "3. String",
          // "4. Complex"};
          //
          //
          // const char *MSGS1[] = {"0. Quit",
          // "1. Init sequence",
          // "2. Add value to sequence",
          // "3. Remove value from sequence",
          // "4. Print sequence",
          // "5. Fill with random values",
          // "6. Sort"};
          //
          // const char *MSGS2[] = {"0. Quit",
          // "1. ListSequence",
          // "2. ArraySequence"};
          //
          // const char *MSGS3[] = {"0. Quit",
          // "1. QuickSort",
          // "2. ShellSort",
          // "3. InsertionSort"};
          if (!type_selected)
            worker.postMessage(choice + '\n' + '4');
          else
            worker.postMessage('0' + '\n' + choice + '\n' + '4');
          type_selected = true;
          break;
        case 'init':
          switch (choice) {
            case 'ListSequence':
              choice = '1';
              break;
            case 'ArraySequence':
              choice = '2';
              break;
          }
          worker.postMessage('1' + '\n' + choice + '\n' + '4');
          break;
        case 'input':
          // console.log('2' + '\n' + choice + '\n' + '4');
          worker.postMessage('2' + '\n' + choice + '\n' + '4');
          break;
        case 'remove':
          worker.postMessage('3' + '\n' + choice + '\n' + '4');
          break;
        case 'fill':
          worker.postMessage('5' + '\n' + choice + '\n' + '4');
          break;
        case 'sort':
          switch (choice) {
            case 'QuickSort':
              choice = '1';
              break;
            case 'ShellSort':
              choice = '2';
              break;
            case 'InsertionSort':
              choice = '3';
              break;
          }
          worker.postMessage('6' + '\n' + choice + '\n' + '4');
          break;
      }
    }
  }

  function print(data) {
    ok = true;
    // console.log(data);
    if (data.includes('Sequence: ['))
      sequence = data.split('Sequence: ')[1];
    else if (data.includes('Result: '))
      result = data.split('Result: ')[1];

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

      <Select text='Select type for sequence' command={(choice)=>{Command('type', choice);}}
              button_text='Select' id='type' options={['int', 'float', 'string', 'complex']} />
      {#if type_selected}
        <div class='my-2 w-full flex flex-wrap justify-center' id='menu'>
          <Input text='Add value to sequence' command={(choice)=>{Command('input',choice);}}
                 button_text='Add' />
          <Input text='Remove value from sequence' command={(choice)=>{Command('remove',choice);}}
                 button_text='Remove' />
          <Input text='Fill sequence with random numbers' command={(choice)=>{Command('fill',choice);}}
                 button_text='Fill' choice={10} />
          <Select text='Init sequence with' command={(choice)=>{Command('init',choice);}}
                  button_text='Init' options={['ArraySequence', 'ListSequence']} />
          <Select text='Sort sequence' command={(choice)=>{Command('sort',choice);}}
                  button_text='Sort' options={['QuickSort', 'ShellSort', 'InsertionSort']} />
          <Field label_text='Sequence' text={sequence} />
          <Field label_text='Result' text={result} />
        </div>
      {/if}
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

