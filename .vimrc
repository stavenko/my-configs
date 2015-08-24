set nocompatible              " be iMproved, required
filetype off                  " required
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

Plugin 'gmarik/Vundle.vim'
Plugin 'flazz/vim-colorschemes'
Bundle "pangloss/vim-javascript"
Plugin 'jelera/vim-javascript-syntax'
Plugin 'nathanaelkane/vim-indent-guides'
Plugin 'moll/vim-node'
Bundle 'scrooloose/syntastic'
Bundle 'Valloric/YouCompleteMe'
Bundle 'marijnh/tern_for_vim'
Plugin 'elzr/vim-json'
Bundle 'scrooloose/nerdtree'
Plugin 'wting/rust.vim'
Bundle 'zah/nimrod.vim'
Bundle 'tpope/vim-fugitive'
Bundle 'fholgado/minibufexpl.vim'
Plugin 'wincent/command-t'
Plugin 'godlygeek/tabular'
Plugin 'plasticboy/vim-markdown'
Plugin 'tpope/vim-surround.git'
Plugin 'tpope/vim-repeat'
call vundle#end()

filetype plugin indent on    " required

filetype plugin on
set expandtab
set cindent

set shiftwidth=4
set tabstop=4
set number

autocmd FileType JavaScript setl shiftwidth=2 tabstop=2
autocmd FileType cpp setl shiftwidth=2 tabstop=2

vnoremap > >gv
vnoremap < <gv

set incsearch
set hlsearch

set t_Co=256
syntax on

set backspace=indent,eol,start

colorscheme distinguished

let g:indent_guides_auto_colors=0
autocmd VimEnter,Colorscheme * :hi IndentGuidesOdd  guibg=red   ctermbg=3
autocmd VimEnter,Colorscheme * :hi IndentGuidesEven guibg=green ctermbg=4
autocmd VimEnter * :MBEOpen 
autocmd VimEnter * :NERDTree
au BufWinEnter * let w:m1=matchadd('Search', '\%<81v.\%>77v', -1)
au BufWinEnter * let w:m2=matchadd('ErrorMsg', '\%>80v.\+', -1)

" c++
au FileType cpp set makeprg=make\ -j9
au FileType cpp nnoremap <F4> :make!<cr>

set colorcolumn=+1
highlight ColorColumn ctermbg=lightred guibg=lightred
let g:syntastic_javascript_checkers = ['jshint', 'jscs']
let g:syntastic_aggregate_errors = 1
let g:syntastic_always_populate_loc_list = 1
let g:ycm_add_preview_to_completeopt=0
let g:ycm_confirm_extra_conf=0
let g:syntastic_check_on_open = 1
let g:syntastic_check_on_wq = 0
set completeopt-=preview

set directory=./.backup//,/tmp//,.

map <F10> :q!<CR>
imap <F10> <ESC>:q!<CR>

map <F2> :w<CR>
imap <F2> <ESC>:w<CR>

map <F3> :MBEFocus <CR>
imap <F3> <ESC>:MBEFocus <CR>

map <F9> :MBEbw <CR>
imap <F9> <ESC>:MBEbw <CR>

