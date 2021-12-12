<script>
  export let options;
  export let text;
  export let button_text;
  export let command;
  let choice;
</script>
<div class='flex my-2 w-full md:w-2/3 pt-2'>
  <div class='relative input-component empty w-full h-8 px-1'>
    <select bind:value={choice} class='px-2 bg-light w-full h-full overflow-hidden rounded-md
          dark:bg-gray-900 dark:text-gray-300 focus:outline-none ring-1 ring-outline-light dark:ring-outline-dark'>
      {#each options as option}
        <option value={option}>
          {option}
        </option>
      {/each}
    </select>
    <label class='absolute left-2 transition-all px-1 bg-transparent dark:text-gray-200 select-none'>
      {text}
    </label>
  </div>
  <div class='px-1 w-1/3 h-8'>
    <button on:click={()=>{command(choice)}} class='h-full w-full light-text dark:bg-alt-dark dark:text-dark-text bg-light rounded-md transition
                    font-semibold focus:outline-none hover:bg-gray-200
                    ring-1 ring-outline-light dark:ring-outline-dark dark:hover:ring-gray-400 duration-300 dark:duration-200'>
      {button_text}
    </button>
  </div>
</div>
<style>
    label {
        top: 0;
        transform: translateY(-100%);
        font-size: 11px;
    }

    .empty input:not(:focus) + label {
        top: 50%;
        transform: translateY(-50%);
        font-size: 14px;
    }

    input:not(:focus) + label {
        color: rgba(70, 70, 70, 1);
    }
</style>