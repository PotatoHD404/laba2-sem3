<script>
  export let button_text;
  export let command;
</script>
<div class='px-1 w-1/3 h-8 pt-1'>
  <button on:click={()=>{command()}} class='h-full w-full light-text dark:bg-alt-dark dark:text-dark-text bg-light rounded-md transition
                    font-semibold focus:outline-none hover:bg-gray-200
                    ring-1 ring-outline-light dark:ring-outline-dark dark:hover:ring-gray-400 duration-300 dark:duration-200'>
    {button_text}
  </button>
</div>
<style>
</style>