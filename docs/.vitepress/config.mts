import { defineConfig } from 'vitepress'

// https://vitepress.dev/reference/site-config
export default defineConfig({
  title: "Jila",
  description: "Jila - experiemental framefork for building cross-platform Lua apps.",
  themeConfig: {
    // https://vitepress.dev/reference/default-theme-config
    nav: [
      { text: 'Home', link: '/' },
      { text: 'Demo', link: '/demo' },
      { text: 'Beginner guide', link: '/guide' },
    ],
    sidebar: [
      {
        text: 'Beginner guide',
        items: [
          { text: 'Introduction', link: '/guide' },
        ]
      }
    ],

    socialLinks: [
      { icon: 'github', link: 'https://github.com/shortice/jila' }
    ]
  }
})
