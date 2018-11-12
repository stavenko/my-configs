
set nocompatible              " be iMproved, required
filetype off                  " required
set rtp+=~/.config/nvim/bundle/Vundle.vim
let vimDir = '$HOME/.config/nvim'
let &runtimepath .= ',' . expand(vimDir . '/bundle/Vundle.vim')
call vundle#rc(expand(vimDir . '/bundle'))

call vundle#begin()

Plugin 'gmarik/Vundle.vim'
Bundle 'scrooloose/nerdtree'
Bundle 'rafi/awesome-vim-colorschemes'
Plugin 'HerringtonDarkholme/yats.vim'
Plugin 'mhartington/nvim-typescript'
Plugin 'Shougo/deoplete.nvim'
Bundle 'tpope/vim-fugitive'
Plugin 'tikhomirov/vim-glsl'
Plugin 'plasticboy/vim-markdown'
Plugin 'yegappan/grep'
Plugin 'rust-lang/rust.vim'
Plugin 'vim-syntastic/syntastic'
Bundle 'Valloric/YouCompleteMe'
Bundle 'mileszs/ack.vim'

call vundle#end()

filetype plugin indent on    " required
filetype plugin on

syntax on

set expandtab
set cindent

autocmd FileType typescript setl shiftwidth=2 tabstop=2
autocmd FileType javascript setl shiftwidth=2 tabstop=2
autocmd FileType cpp setl shiftwidth=2 tabstop=2
autocmd FileType rust setl shiftwidth=2 tabstop=2

command! -bar -buffer -nargs=* Gcm Gcommit --no-verify "<q-args>"

au FileType typescript map ˆ :TSDef <CR>
au FileType rust nmap gd <Plug>(rust-def)
au FileType rust nmap gs <Plug>(rust-def-split)
au FileType rust nmap gx <Plug>(rust-def-vertical)
au FileType rust nmap <leader>gd <Plug>(rust-doc)

" let g:tsuquyomi_disable_default_mappings=1
" let g:tsuquyomi_disable_quickfix=1
let g:nvim_typescript#default_mappings=0
let g:syntastic_check_on_open=1
let g:syntastic_always_populate_loc_list = 0
" let g:syntastic_javascript_checkers=['eslint']
" let g:syntastic_typescript_checkers=['tsuquyomi']
" let g:syntastic_javascript_eslint_exe='npx eslint'
" let g:syntastic_rust_checkers=['cargo']

map <leader>n :NERDTreeToggle<CR>
map <leader>f :NERDTreeFind<CR>

set termguicolors
set background=dark
colorscheme solarized8

set number

