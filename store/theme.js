export const state = () => ({
    dark: false
})

export const mutations = {
    toggle(state) {
        state.dark = !state.dark;
    },
}