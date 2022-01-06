<script>
  export let label_text;
  export let text;
</script>
<div class='flex my-2 w-full md:w-2/3 pt-1'>
  <div class='relative input-component empty w-full h-8 px-1'>
    <input bind:value={text} type='text' name='items-input' class='px-2 bg-light w-full h-full overflow-hidden rounded-md
          dark:bg-gray-900 dark:text-gray-200 focus:outline-none ring-1 ring-outline-light dark:ring-outline-dark'
           disabled>
    <label class='absolute left-2 transition-all px-1 bg-transparent dark:text-gray-200 select-none'>
      {label_text}
    </label>
  </div>
</div>
<style>
    label {
        pointer-events: none;
        color: rgba(70, 70, 70, 1);
        top: 0;
        transform: translateY(-100%);
        font-size: 11px;
    }
</style>