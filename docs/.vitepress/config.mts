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
      { text: 'Beginner guide', link: '/guide' }
    ],
    sidebar: [
      {
        text: 'Beginner guide',
        link: "/guide",
        items: [
          { text: 'Build first app', link: '/guide/first' },
        ]
      },
      {
        text: "Modules",
        link: "/modules",
        items: [
          { text: 'Dear ImGui', link: '/modules/imgui' },
          { text: 'Filesystem', link: '/modules/fs' },
          { text: 'Network', link: '/modules/net' },
          { text: 'SDL3', link: '/modules/sdl3' },
          { text: 'System (OS-Specific API)', link: '/modules/system' },
          { text: 'Engine & Properties', link: '/modules/engine_props'},
          { text: 'AI inference', link: '/modules/ai_inference'},
          { text: 'Writing custom module', link: 'modules/custom'}
        ]
      },
      {
        text: "Architecture",
        link: "/arch",
        items: [
          { text: 'What is module', link: '/arch/modules' },
          { text: 'Threads', link: '/arch/threads' },
          { text: 'Events', link: '/arch/events' },
          { text: 'Limitations', link: '/arch/limitations'}
        ]
      }
    ],

    socialLinks: [
      { icon: 'github', link: 'https://github.com/shortice/jila' }
    ]
  }
})
