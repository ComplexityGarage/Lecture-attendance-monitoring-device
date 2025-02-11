<template>
    <Head title="Dashboard" />

    <AuthenticatedLayout>
        <template #header>
            <h2 class="text-xl font-semibold leading-tight text-gray-800">
                Nazwa Przedmiotu
            </h2>
        </template>

        <div class="max-w-7xl mx-auto py-6 px-4 sm:px-6 lg:px-8">
            <div class="bg-white overflow-x-auto p-5 border border-stone-200 rounded-2xl flex items-center gap-10">
                <div class="relative">
                    <svg width="208" height="208" viewBox="0 0 208 208" style="transform: rotate(-90deg)">
                        <circle r="80" cx="104" cy="100" fill="transparent" stroke-width="30" class="stroke-[#e1e7fe]"></circle>
                        <circle r="80"
                                cx="104"
                                cy="100"
                                fill="transparent"
                                stroke-linecap="round"
                                stroke-width="30"
                                stroke-dasharray="439.6px"
                                :stroke-dashoffset="progress_state"
                                class="stroke-[#5046e5]"
                        ></circle>
                    </svg>
                    <div class="absolute top-1/2 left-1/2 -translate-x-1/2 -translate-y-1/2 text-center text-gray-700 font-semibold text-2xl">
                        30%
                    </div>
                    </div>
                Studenci w sali: {{ visits.length }}
                <input v-model="expectedStudentsCount">

                <button @click.prevent="resetVisitors">Rozpocznij zajęcia</button>
            </div>
        </div>

        <div class="max-w-7xl mx-auto py-6 px-4 sm:px-6 lg:px-8">
            <div class="bg-white rounded-2xl border border-stone-200 overflow-x-auto">
                <div class="py-4 px-6 font-semibold text-xl border-b border-stone-200">
                    Studenci
                </div>
                <table class="w-full whitespace-nowrap">
                    <thead>
                        <tr class="text-left font-bold">
                            <th class="py-2 px-6 bg-[#f9fbfc]">ID</th>
                            <th class="py-2 px-6 bg-[#f9fbfc]">Hash</th>
                            <th class="py-2 px-6 bg-[#f9fbfc]">Name</th>
                            <th class="py-2 px-6 bg-[#f9fbfc]">Date</th>
                        </tr>
                    </thead>
                    <tbody>
                        <tr
                            v-for="visit in visits"
                            :key="visit.id"
                            class="hover:bg-gray-100 focus-within:bg-gray-100"
                        >
                            <td class="border-t p-5 font-bold">
                                {{ visit.id }}
                            </td>
                            <td class="border-t p-5">
                                {{  visit.hash }}
                            </td>
                            <td class="border-t p-5">-</td>
                            <td class="w-px border-t p-5">
                                {{ formattedDate(visit.created_at) }}
                            </td>
                        </tr>
                        <tr v-if="visits.length === 0">
                            <td class="px-6 py-4 border-t" colspan="4">
                                No visits found.
                            </td>
                        </tr>
                    </tbody>
                </table>
            </div>
        </div>
    </AuthenticatedLayout>
</template>

<script>
import AuthenticatedLayout from "@/Layouts/AuthenticatedLayout.vue";
import { Head } from "@inertiajs/vue3";

export default {
    components: {
        AuthenticatedLayout,
        Head,
    },

    props: {
        visitsOnServer: Object,
    },

    data: () => ({
        visits: [],
        expectedStudentsCount: 20
    }),

    computed: {
        progress_state() {
            return 439.6 - ((this.visits.length*100)/30 * 439.6) / 100;
        }
    },

    methods: {
        formattedDate(date) {
            return this.$date(date)
        },
        resetVisitors() {
            this.$inertia.post(route('visitors.reset'))
            this.visits = [];
        }
    },

    created() {
        Echo.private(`visits`).listen("VisitCreated", (e) => {
            this.visits.unshift(e.visit);
        });
    },

    mounted() {
        this.visits = [...this.visitsOnServer];
    },
};
</script>